-- 13. Names of all people who starred in a movie in which Kevin Bacon also starred
SELECT DISTINCT p.name FROM people as p JOIN stars as s ON p.id = s.person_id WHERE s.movie_id IN (
    SELECT s.movie_id FROM stars as s
    JOIN people as p ON s.person_id = p.id
    WHERE p.name = 'Kevin Bacon' AND p.birth = 1958
)
AND p.name != 'Kevin Bacon';
