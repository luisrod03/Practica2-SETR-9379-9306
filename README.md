Este proyecto demuestra el uso de arquitecturas de software modulares en sistemas embebidos. 
Se controlan tres LEDs mediante señales PWM de hardware cuya intensidad es proporcional a la lectura de tres potenciometros a traves del convertidor Analogico-Digital en modo OneShot.

El sistema esta estructurado en modulos separados. 
La innovacion principal radica en la reutilizacion de memoria: se desarrollo una unica funcion de tarea generica. 
Mediante el puntero pvParameters de FreeRTOS, se inyectan estructuras estaticas constantes durante la creacion de las tareas que indican a cada instancia que canal ADC leer y que canal PWM modificar.


En conclusion, el uso avanzado de punteros y pvParameters en FreeRTOS transforma el desarrollo de sistemas embebidos, 
permitiendo crear codigo altamente escalable, limpio y seguro. La modularidad alcanzada facilita el mantenimiento, 
protege los recursos de memoria y valida que un diseño bien estructurado elimina la necesidad de redundancia funcional en sistemas multicanal.

Preguntas Guia
1. Por que es preferible pasar la configuracion de canal mediante pvParameters en lugar de usar variables globales o funciones de tarea distintas para cada canal?
Fomenta la encapsulacion y ahorra memoria Flash. Evita duplicar codigo de forma innecesaria y previene colisiones de datos y condiciones de carrera que ocurririan si se utilizaran variables globales.

2. Que sucederia si los bloques task_params_t se declararan como variables locales en tasks_create_all en lugar de static? Como lo detectarias experimentalmente?
Las variables locales se destruyen al finalizar la funcion. Las tareas intentarian leer direcciones de memoria liberada.
El sistema fallaria arrojando un error provocando un reinicio del microcontrolador, o los actuadores se comportarian de forma impredecible.

4. Las tres tareas tienen el mismo periodo pero prioridades distintas. En que situacion se hace visible la diferencia de prioridad en la salida del terminal?
Cuando las tareas despiertan simultaneamente en el mismo tick del procesador tras su tiempo de bloqueo.
El planificador otorgara la CPU y el canal de UART primero a la tarea de mayor prioridad, asegurando un orden de impresion determinista.

6. Por que se usa vTaskDelay en lugar de un ciclo for con retardo de software? Que diferencia implica para el planificador?
vTaskDelay transfiere la tarea al estado Bloqueado, cediendo inmediatamente el control del procesador a otras tareas.
Un ciclo for genera espera activa, secuestrando la CPU en estado Ejecutando e impidiendo la multitarea.

8. Que valor esperarias en el stack watermark de la tarea con menor prioridad comparado con el de mayor prioridad? Por que podrian diferir?
Los valores son practicamente identicos dado que ejecutan exactamente la misma instruccion en memoria.
Unicamente diferirian por unos pocos bytes si una interrupcion asincrona de hardware ocurre en un punto distinto de la ejecucion de cada tarea.

10. Si se añadiera un cuarto potenciometro y LED, que cambios minimos requeriria el codigo?
Solo requeriria declarar un nuevo struct estatico, mapear los pines correspondientes en los arreglos de configuracion del hardware y mandar llamar a xTaskCreate una vez mas.
La logica de la funcion de la tarea queda intacta.
