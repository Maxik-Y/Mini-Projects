-- 12. Titles of all of movies in which both Jennifer Lawrence and Bradley Cooper starred
SELECT title FROM movies WHERE id IN (
    SELECT s.movie_id FROM stars as s
    JOIN people as p ON s.person_id = p.id
    WHERE p.name = 'Bradley Cooper'
)
AND id IN (
    SELECT s.movie_id FROM stars as s
    JOIN people as p ON s.person_id = p.id
    WHERE p.name = 'Jennifer Lawrence'
);
