-- 11. Titles of the five highest rated movies (in order) that Chadwick Boseman starred in, starting with the highest rated
SELECT m.title FROM movies as m
JOIN stars as s ON m.id = s.movie_id
JOIN people as p ON s.person_id = p.id
JOIN ratings as r ON m.id = r.movie_id
WHERE p.name = 'Chadwick Boseman'
ORDER BY ratings.rating DESC LIMIT 5;
