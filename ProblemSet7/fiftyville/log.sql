-- Problem set 7: Fiftyville
--
-- Keep a log of any SQL queries you execute as you solve the mystery.
--
-- First query: Investigate the given hint
SELECT
    description as "FIRST CLUE" 
FROM
    crime_scene_reports
WHERE
    street IS "Humphrey Street"
    AND YEAR IS 2021
    AND MONTH IS 7
    AND DAY IS 28
    AND LOWER(description) LIKE "%theft%";


-- Conclussion: 
--      Theft took place at 10:15am at bakery.
--      Three witnesses and interviews were conducted.
--
-- Second query: Search for interviews 
SELECT
    transcript AS "LEAD(s)"
FROM
    interviews
WHERE
    YEAR IS 2021
    AND MONTH IS 7
    AND DAY IS 28
    AND transcript LIKE "%thief%";


-- Conclussion:
--      lead #1: Thief got into the car and drove away -> Check 'bakery_security_log'.
--      lead #2: Prior to the theft, the suspect withdrawed some money on Leggett Street -> Check ´atm_transactions´ 
--          and 'bank_accounts'
--      lead #3: Thief called someone and spoke for less than a minute. -> Check 'phone_calls'
--      lead #4: In the phone call, they spoke about takink 'earliest flight out of Fiftyville tomorrow' -> Check 'Flights'
--
-- Third query: List of all people yielded by the leads 
SELECT
    name AS "THIEF"
FROM
    people
WHERE
    id IN (
        SELECT
            person_id
        FROM
            bank_accounts
        WHERE
            -- list of people withdrawing money
            account_number IN (
                SELECT
                    account_number
                FROM
                    atm_transactions
                WHERE
                    atm_location IS "Leggett Street"
                    AND transaction_type IS "withdraw"
                    AND YEAR IS 2021
                    AND MONTH IS 7
                    AND DAY IS 28
            )
            -- list of all license plates leaving the bakery
            AND license_plate IN (
                SELECT
                    license_plate
                FROM
                    bakery_security_logs
                WHERE
                    YEAR IS 2021
                    AND MONTH IS 7
                    AND DAY IS 28
                    AND HOUR IS 10
                    AND MINUTE BETWEEN 15 AND 25
                    AND activity IS "exit"
            )
            -- list of all out-going calls on that day with matching duration
            AND phone_number IN (
                SELECT
                    caller
                FROM
                    phone_calls
                WHERE
                    YEAR IS 2021
                    AND MONTH IS 7
                    AND DAY IS 28
                    AND duration < 60
            )
            -- lift of all people taking the EARLIEST flight the very next day
            AND passport_number IN (
                SELECT
                    passport_number
                FROM
                    passengers
                WHERE
                    flight_id IN (
                        SELECT
                            id
                        FROM
                            flights
                        WHERE
                            YEAR IS 2021
                            AND MONTH IS 7
                            AND DAY IS 29
                            AND origin_airport_id IN (
                                SELECT
                                    id
                                FROM
                                    airports
                                WHERE
                                    city LIKE "Fiftyville%"
                            )
                        ORDER BY
                            YEAR,
                            MONTH,
                            DAY,
                            HOUR,
                            MINUTE
                        LIMIT
                            1
                    )
            )
    );


-- Fourth query: find the destination of the flight 
SELECT
    city AS "ESCAPED TO"
FROM
    airports
WHERE
    id IS (
        SELECT
            destination_airport_id
        FROM
            flights
        WHERE
            id IS (
                SELECT
                    flight_id
                FROM
                    passengers
                WHERE
                    passport_number IS (
                        SELECT
                            passport_number
                        FROM
                            people
                        WHERE
                            name IS "Bruce"
                    )
            )
    );


-- Fifth query: find the call receiver
SELECT
    name AS "ACCOMPLICE"
FROM
    people
WHERE
    phone_number IS (
        SELECT
            receiver
        FROM
            phone_calls
        WHERE
            YEAR IS 2021
            AND MONTH IS 7
            AND DAY IS 28
            AND duration < 60
            AND caller IS (
                SELECT
                    phone_number
                FROM
                    people
                WHERE
                    name IS "Bruce"
            )
    );
