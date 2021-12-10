# KursachOOP
## About
This is an OOP group course work. The task is:

Передбачити кілька різних типів транспортних засобів (швидкі легкові авто, вантажні 
авто з обмеженнями на проїзд по певних шляхах, електричні авто, автобуси тощо) та 
транспортних шляхів (різна дозволена швидкість руху, обмеження на рух вантажівок 
тощо). Задати конфігурацію шляхів між 5-10 "точками" (адресами, заправками, 
зупинками). Змоделювати рух транспортних засобів залежно від їх задач (доставка 
товару чи пасажирів від точки А до Б, необхідність заправок пальним тощо). Автомобілі 
мають певні алгоримти прокладання шляху (передбачити маршрути з проміжними 
зупинками). 
Доцільно передбачити чергу задач (прямувати до пункту А, заправитись в пункті Б 
тощо) для кожного учасника руху, яку опрацьовувати згідно віртуального плину часу у 
світі, що моделюється. Вхідні дані: конфігурація шляхів, учасники руху та їх задачі. Далі 
циклічно змінюється віртуальний час, і відповідно до цього опрацьовуються зміна 
положення та черги задач учасників руху. Зміни положення учасників руху та настання 
подій (заправка, посадка-висадка пасажирів) слід відображати текстовими 
повідомленнями в консолі (ЛР) або графічно (КР). 
Варіанти розподілу відповідальності в команді: а) підготовка вхідних даних (дорожня 
мережа) та сценарію моделювання (пасажири, вантажі, їх точки призначення); б) 
алгоритми пошуку маршруту транспортними засобами, наповнення черги задач 
точками маршруту; в) оновлення стану транспортних засобів (переміщення, робота з 
чергою задач) та інших об’єктів на кожному кроці симуляції.
## Diagrams
![Use case diagram](UseCaseDiagram.png?raw=true "Use case diagram")
![Class diagram](ClassDiagram.png?raw=true "Class diagram")
## How to build and run
From command line using git and cmake:
```
git clone https://github.com/DeNiCoN/KursachOOP.git
cd KursachOOP
cmake -B build -S .

cd build
cmake --build .

./KursachOOP
```

Or download repository and use cmake

![image](https://user-images.githubusercontent.com/29448585/145541437-8537dd3a-b057-4bac-915a-cf179ef2a486.png)
![image](https://user-images.githubusercontent.com/29448585/145541483-66c9164a-f9cd-4dda-ac65-2f5690d3d10f.png)
