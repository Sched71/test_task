# Тестовое задание
Программа компилировалась на Ubuntu 22.04.5 LTS c помошю компилятора gcc version 14.2.0 (GCC). Для сборки использовался Cmake version 3.10, для тестов -- Googletest.

# Сборка

Сначала перейти в директорию проекта.

Чтобы собрать проект, вызвать:
```sh 
./build.sh
```

После сборки выполнить тесты:
```sh 
./run_tests.sh
```

Запустить программу (вместо "src/input" можно использовать относительный путь своего файла):
```sh 
./run.sh src/input
```