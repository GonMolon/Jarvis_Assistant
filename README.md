# Jarvis
Asistente personal Jarvis.

-------------------------------------------------------------------------------
Para cargar nuevos archivos de audio:
-------------------------------------------------------------------------------
Grabar las frases con lumivox y audacity. Volumen al maximo y sin auriculares va bien. 
Pasar la pista de estéreo a mono y exportarla como .wav a la carpeta audio.

Abrir en modo administrador quickSynthesis. (MODO RSC4 family). Abrir el archivo sounds.qxp 
(tabla de sonidos). Añadir los audios nuevos. Edit compression details, seleccionar 8-BIT PCM 9.3K 
(o maximo que se pueda mientras que quede memoria, actualmente haria falta por debajo de 4-bit), 
seleccionar max en advanced-de-emphasis on playback. Seleccionar todo y click en build.

Cargar EasyVRBridge. Poner jumper en "Up". Abrir easyvr commander, file, update custom table. 
Importamos la tabla de sonidos, activamos slow transfer y subimos.

Borramos en SOUNDS.h todo menos los define.


-------------------------------------------------------------------------------
Para grabar nuevos comandos:
-------------------------------------------------------------------------------
Poner jumper en "Sw". Abrir easyvr commander y conectar a arduino. La shield tiene que estar 
conectada directamente a arduino.


-------------------------------------------------------------------------------
Para cargar el programa:
-------------------------------------------------------------------------------
Poner jumper en "Sw". La shield puede estar como sea.


//static unsigned int VENT_LEVEL_1[99] = {450, 700, 500, 700, 500, 1600, 500, 1550, 550, 1550, 500, 1600, 450, 1600, 500, 700, 500, 1600, 450, 750, 450, 1600, 550, 650, 450, 4600, 450, 750, 450, 750, 500, 1550, 450, 1600, 500, 1600, 500, 1550, 500, 1600, 500, 700, 500, 1600, 450, 750, 450, 1600, 500, 700, 500, 4550, 500, 700, 450, 700, 500, 1600, 500, 1600, 450, 1600, 500, 1600, 450, 1600, 500, 700, 500, 1600, 500, 700, 450, 1600, 500, 700, 500, 4700, 450, 750, 450, 700, 500, 1600, 450, 1600, 500, 1600, 450, 1650, 450, 1600, 500, 700, 500, 1600, 450, 700, 500};
//static unsigned int VENT_LEVEL_2[99] = {450, 750, 400, 750, 500, 1600, 450, 1600, 450, 1650, 450, 1650, 450, 1600, 500, 700, 500, 700, 450, 1600, 450, 800, 400, 750, 450, 4600, 450, 750, 450, 750, 400, 1650, 450, 1650, 500, 1550, 450, 1650, 450, 1650, 400, 800, 400, 750, 450, 1650, 450, 750, 500, 700, 400, 4600, 450, 750, 450, 750, 500, 1550, 450, 1650, 450, 1650, 450, 1600, 450, 1650, 450, 750, 450, 700, 450, 1650, 450, 750, 500, 700, 450, 4700, 450, 750, 450, 750, 500, 1550, 500, 1600, 450, 1650, 500, 1550, 450, 1650, 500, 700, 450, 750, 500, 1550, 500};

