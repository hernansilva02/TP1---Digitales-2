# TP1 - Digitales 2 - Emulador de Medidor de potencia aparente

La idea es emular un medidor de potencia de electrodomésticos. Se leen los datos del ADC
para determinar el nivel de corriente y la tensión es fija 220 V. S = V x I

## Que se computa (inputs)
- Corriente -> es la conversión de la tensión que manda el ADC, la
  relación es 3.3 V / 15 A = 0.22 V/A. Cada .22 Volts marca 1 A. Relación lineal.
- Formato del output, el usuario cambia la unidad de medida con el boton integrado de la
  LPC. Puede ser: W, A, Costo ($3600 / Wh).
- Intervalo de tiempo: Comando por USART que indica el intervalo, puede ser 5 s o 10 s


## Cúal es el output
- Reporte de los datos por la terminal (USART) <br>
Formato:<br>

1- 2200W 5seg o 10.0A 5seg o $6100 5seg.<br>
2- 2200W 10seg o 10.0A 10seg o $12200 10seg.<br>
3- 2200W 15seg o 10.0A 15seg o $18300 15seg.<br>
4- 2200W 20seg o 10.0A 20seg o $24400 20seg.<br>

- LED integrado de la placa<br>

| Color    | Indicacion                      |
| :-------:| :-----------------------------: |
| Azul     | Corrriente entre 1.5 A y 4.5 A  |
| Verde    | Corriente entre 5.25 A y 9.75 A |
| Rojo     | Corriente mayor a 10.5 A        |
