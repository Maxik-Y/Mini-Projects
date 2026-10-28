-- 7. All movies and ratings from 2010, in decreasing order by rating (alphabetical for those with same rating)
SELECT m.title, r.rating FROM movies as m JOIN ratings as r ON m.id = r.movie_id WHERE year = 2010 ORDER BY rating DESC;
