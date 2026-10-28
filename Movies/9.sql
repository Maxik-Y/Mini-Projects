-- 9. Names of all people who starred in a movie released in 2004, ordered by birth year
SELECT DISTINCT p.id, p.name FROM people as p JOIN stars as s ON p.id = s.person_id WHERE s.movie_id IN (SELECT id FROM movies WHERE year = 2004) ORDER BY birth;
