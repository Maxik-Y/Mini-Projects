-- 8. Names of people who starred in Toy Story
SELECT name FROM people WHERE id IN (SELECT s.person_id FROM movies as m JOIN stars as s ON m.id = s.movie_id WHERE m.title = 'Toy Story');
