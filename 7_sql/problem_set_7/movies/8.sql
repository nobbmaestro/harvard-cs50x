/* Problem set 7: Movies, task 8

Write a SQL query to list the names of all people who starred in Toy Story.
- Your query should output a table with a single column for the name of each person.
- You may assume that there is only one movie in the database with the title Toy Story.
*/
SELECT
    name AS "Stars in Toy Story"
FROM
    people
WHERE
    id IN (
        SELECT
            person_id
        FROM
            stars
        WHERE
            movie_id IS (
                SELECT
                    id
                FROM
                    movies
                WHERE
                    title IS "Toy Story"
            )
    )
ORDER BY
    name ASC;
