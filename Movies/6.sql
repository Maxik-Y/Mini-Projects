-- 6. Average rating of movies in 2012
SELECT Avg(r.rating) FROM movies as m JOIN ratings as r ON m.id = r.movie_id WHERE year = 2012;
