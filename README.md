#  Problema de los Filósofos Comelones en C

##  Descripción
Este proyecto implementa el clásico **problema de los filósofos comelones** (también conocido como *Dining Philosophers Problem*), utilizando el lenguaje **C** en **Linux**.  
El objetivo es simular cómo un grupo de filósofos alternan entre **pensar** y **comer**, compartiendo recursos limitados (los tenedores) sin generar **condiciones de carrera**, **interbloqueo (deadlock)** ni **inanición (starvation)**.

---

## ⚙️ Archivos incluidos
| Archivo | Descripción |
|----------|--------------|
| `filosofos.c` | Versión inicial del problema, sin control de concurrencia. |
| `filosofosMutex.c` | Versión con sincronización básica usando mutex. |
| `filosofosMutexTenedores.c` | Versión final que soluciona los problemas de *race condition*, *deadlock* y *starvation*. |
| `README.md` | Documento explicativo del proyecto. |
| `Dining-philosophers.jpg` | Imagen ilustrativa del problema. |

---

##  Análisis de la solución
La versión final (`filosofosMutexTenedores.c`) utiliza **mutex (mutual exclusion locks)** para garantizar que solo un filósofo pueda tomar un tenedor a la vez.  
Además, se establece un **orden de adquisición de los recursos** (tenedores) para evitar ciclos de espera circular, lo cual previene el *deadlock*.

**Cómo se evita cada problema:**

-  **Race Condition:**  
  Se utilizan **mutex** para proteger las secciones críticas donde los filósofos toman o dejan los tenedores.

-  **Deadlock:**  
  Se impone una regla: cada filósofo debe tomar primero el tenedor de la izquierda y luego el de la derecha (o viceversa en el caso de uno de ellos), evitando así el bloqueo circular.

-  **Starvation:**  
  Los filósofos alternan entre pensar y comer, garantizando que todos tengan oportunidad de acceder a los recursos de manera equitativa.

---

##  Ejecución en Linux
###  Compilar el programa
Abre una terminal en la carpeta del proyecto y ejecuta:
```bash
gcc filosofosMutexTenedores.c -o filosofos -lpthread
./filosofos
