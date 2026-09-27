# PA03_Computaci-n-Gr-fica

# Producto Académico 3: 

Este proyecto corresponde a la implementación del Producto Académico 3 de la asignatura Computación Gráfica. Consiste en el diseño e implementación de una escena tridimensional interactiva de una cámara de observación astronómica y planetario óptico construida en C++ utilizando OpenGL y GLUT, estructurada modularmente mediante CMake. El prototipo incorpora 6 objetos 3D diferenciables, control de visibilidad mediante Depth Buffer (Z-Buffer), 2 fuentes de iluminación simultáneas (direccional cenital y puntual cálida móvil), aplicación del modelo de iluminación de Phong, asignación de materiales diferenciados, mapeo de textura 2D (formato BMP), conmutación de modelos de sombreado (Smooth y Flat), una cámara orbital con tres vistas predefinidas y un efecto complementario de animación continua en tiempo real.

## Requisitos del Sistema

* Compilador de C++ compatible con C++17 (GCC/MinGW, Clang o MSVC).
* CMake (versión 3.10 o superior).
* Bibliotecas de desarrollo de OpenGL y FreeGLUT / GLUT instaladas en el sistema.

## Compilación y Ejecución

### Windows (MinGW Makefiles)

Para generar los archivos de compilación y compilar desde la raíz del proyecto (`PA3/`):

```bash
mkdir build
cd build
cmake -G "MinGW Makefiles" ..
cmake --build .
```

Para ejecutar el binario asegurando el enlace de los recursos (assets/):

```Bash
cd ..
.\build\render3d.exe
```

Controles de Interacción y Experimentación
- L: Encender o apagar la el foco de la lámpara.
- J / K: Trasladar la posición de la Luz 1 hacia la izquierda o derecha sobre el eje X.
- M: Alternar cíclicamente el material del orbe central.
- S: Alternar el modelo de sombreado entre suave (GL_SMOOTH) y plano facetado (GL_FLAT).
- T: Activar o desactivar la textura del mapa estelar sobre el panel mural.
- B: Habilitar o deshabilitar el Depth Buffer para comprobar la oclusión y visibilidad geométrica.
- V: Alternar cíclicamente entre las 3 vistas de cámara (Perspectiva general, Superior cenital y Lateral).
- Flechas direccionales: Orbitar la cámara libremente alrededor del escenario.
- \+ / -: Acercar o alejar el zoom de la cámara.
- ESC: Cerrar la aplicación.

*Elaboración*

Asignatura: Computación Gráfica

Institución: Universidad Continental

Docente: Mg. Percy Maldonado Quispe

Integrante: Erwin Alain Felix Tayro Mosqueira

*Licencia*

Este proyecto se distribuye bajo la Licencia MIT. Para más detalles, consulte los términos estándar de código abierto.
