# 🌡️ Sistema de Monitoramento IoT

[![Status: Concluído](https://img.shields.io/badge/Status-Concluído-brightgreen.svg)]()
[![Plataforma: Wokwi](https://img.shields.io/badge/Plataforma-Wokwi-blue.svg)]()
[![Broker: HiveMQ](https://img.shields.io/badge/Broker-HiveMQ_Cloud-orange.svg)]()

## 👥 Feito por:
* **Nome:** Pedro Sakai - **RM:** 565956


Projeto de monitoramento de temperatura e distância utilizando ESP32, integrando dados de sensores reais com APIs externas e persistência em banco de dados relacional.

## 📋 Descrição do Projeto
O sistema simula o monitoramento de uma máquina. O **ESP32** coleta dados de temperatura e proximidade. Esses dados são enviados via protocolo **MQTT** para o **Node-RED** e armazena tudo em um banco de dados **MySQL**. A interface final é exibida em um Dashboard interativo.

## 🏗️ Arquitetura da Solução
A solução foi desenhada seguindo a arquitetura de referência para sistemas IoT:

1.  **Sensores (Camada de Percepção):** DHT22 (Temperatura) e HC-SR04 (Distância).
2.  **Processamento:** ESP32 realizando a leitura e publicação MQTT.
3.  **Comunicação (MQTT):** Envio seguro via TLS (porta 8883) para o HiveMQ Cloud.
4.  **Backend (Node-RED):** Orquestração dos dados, consumo de API ViaCEP e integração MySQL.
5.  **Visualização (Dashboard):** Interface HTML para monitoramento em tempo real.

## 🛠️ Tecnologias Utilizadas
*   **Hardware Simulado:** ESP32 (Wokwi)
*   **Linguagem:** C++ (Arduino IDE/Framework)
*   **Protocolo:** MQTT (PubSubClient)
*   **Serviço de Nuvem:** HiveMQ Cloud
*   **Orquestrador:** Node-RED
*   **Banco de Dados:** MySQL
*   **API Externa:** ViaCEP

## DASHBOARD
![Dashboard](assets/dashboard.png)

## ESP32 simulado no Wokwi
![ESP32 no Wokwi](assets/esp.png)

## ⚙️ Instruções de Execução

### 1. Configuração do ESP32
No Wokwi, abra o código do sketch.ino.

Configure as constantes mqtt_user e mqtt_pass com suas credenciais do HiveMQ Cloud.

Inicie a simulação.

### 2. Configuração do Node-RED
Importe o arquivo flows.json.

Instale as bibliotecas node-red-dashboard e node-red-node-mysql através do menu "Manage Palette".

No nó MQTT, configure o servidor Cloud e habilite o TLS.

No nó MySQL, insira as credenciais do seu banco de dados.

### 3. Configuração do Banco de Dados
Crie a tabela necessária utilizando o script abaixo:
```sql
CREATE DATABASE projeto_iot;
USE projeto_iot;

CREATE TABLE monitoramento (
    id INT AUTO_INCREMENT PRIMARY KEY,
    temperatura FLOAT,
    distancia FLOAT,
    cep VARCHAR(10),
    cidade VARCHAR(100),
    data_hora TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

