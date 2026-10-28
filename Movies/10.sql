-- 10. Names of all directors who have directed a movie that got a rating of at least 9.0
SELECT p.name FROM people as p JOIN directors as d ON p.id = d.person_id WHERE d.movie_id IN (SELECT m.id FROM movies as m JOIN ratings as r ON m.id = r.movie_id WHERE r.rating >= 9.0);
