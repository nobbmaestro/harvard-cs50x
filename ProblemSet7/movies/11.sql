/* Problem set 7: Movies, task 11

Write a SQL query to list the titles of the five highest rated movies (in order) that Chadwick Boseman starred in, 
starting with the highest rated.
- Your query should output a table with a single column for the title of each movie.
- You may assume that there is only one person in the database with the name Chadwick Boseman.
*/
SELECT
    movies.title
FROM
    movies
    JOIN ratings ON movies.id = ratings.movie_id
WHERE
    id IN (
        SELECT
            movie_id
        FROM
            stars
        WHERE
            person_id IN (
                (
                    SELECT
                        id
                    FROM
                        people
                    WHERE
                        name IS "Chadwick Boseman"
                )
            )
    )
ORDER BY
    ratings.rating DESC
    limit 5;
