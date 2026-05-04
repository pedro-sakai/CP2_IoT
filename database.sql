CREATE DATABASE IF NOT EXISTS projeto_iot;
USE projeto_iot;

CREATE TABLE IF NOT EXISTS monitoramento (
    id INT AUTO_INCREMENT PRIMARY KEY,
    sensor_tipo VARCHAR(50),
    valor FLOAT,
    timestamp DATETIME DEFAULT CURRENT_TIMESTAMP
);