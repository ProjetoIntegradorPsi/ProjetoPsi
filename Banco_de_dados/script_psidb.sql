DROP DATABASE IF EXISTS psidb;
CREATE DATABASE psidb;
USE psidb;

CREATE TABLE tank (
  id INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
  nme VARCHAR(6),
  date_time DATETIME,
  temp_in DECIMAL(3,1),
  temp_out DECIMAL(3,1),
  ph DECIMAL(3,1),
  oxi DECIMAL(3,1),
  volt DECIMAL(5,2),
  currnt DECIMAL(4,2),
  poten DECIMAL(4,2),
  cond DECIMAL(4,1)
);

-- SELECT * FROM tank;