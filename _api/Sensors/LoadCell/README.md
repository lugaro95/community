# Modulo de control de balanza

## Descripción
Este es un módulo de control de balanza que permite la medición del peso y el control básico de una balanza. A continuación se detallan las variables, funciones y eventos que son accesibles o no accesibles para el usuario.

## Variables

### Variables accesibles para el usuario

Nombre | Tipo | Descripción
-------|------|-------------
"Peso" | float | Valor del peso actual.
"Capacidad" | float | Peso maximo para el cual la balanza es lineal.
"mVxV" | float | Relación entre la tensión de salida frente al peso calibrado a una tensión de alimentación de 1V.
"mVxV_cal" | float | Valor de mVxV dado por la balanza.

### Variables no accesibles para el usuario

Nombre | Tipo | Descripción
-------|------|-------------
"K" | float | Pendiente de respuesta de la balanza.
"Cero" | int32 | Ordenada al origen.
"Corrimiento" | int32 | Contiene el offset actual que se produce por la deformación de la balanza.
"Historial" | int32[32] | Cola circular utilizada para filtrar el ruido en las mediciones. Frente a una variación muy abrupta (5 varianzas), todos los valores seran reemplazados por la ultima medicion, esto para obtener una buena respuesta en el tiempo frente a los cambios.
"Acumulador" | int64 | Posee la suma de todos los valores dentro del Historial.

## Funciones

### Funciones accesibles para el usuario

- `serZero(void)`: Establece el valor actual como el cero.
- `setReference(float Peso_de_referencia)`: Establece el valor de peso para la actual medida, de forma que se calcule la respuesta de la balanza.
- `setmVxV(float mVxV)`: Establece el valor de mVxV_cal.

### Funciones no accesibles para el usuario
 
- `float nuevaLectura(int32 nuevo_valor)`: Se encarga de obtener el nuevo valor medido por el sensor y lo refleja en el Peso, para esto elimina el ultimo valor del Historial e ingresa el nuevo valor, pero en vez de volver a sumar todos los datos, resta del acumulador el valor eliminado y suma el valor nuevo.
- `balanza_poll(void)`: Este metodo se encarga del control basico del modulo, asi como la invocación a los diferentes eventos.
- `balanza_init(void)`: Inicializa los valores necesarios para el correcto funcionamiento del modulo.

## Eventos

### Eventos accesibles para el usuario

- `zero(void)`: Se ejecuta cuando la balanza se estabiliza en cero.
- `estable(void)`: Se ejecuta cuando la balanza se estabiliza en un valor.
- `capacidadMaximaSuperada(void)`: Se ejecuta cuando se pesa algo que iguala o supera la capacidad maxima de la balanza.