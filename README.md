# Neural-and-console-ui

# 🧠 Нейросеть для распознавания X и O в консоли

Это консольное приложение позволяет рисовать символы **X** и **O** в "ручном" режиме через UI в терминале и распознаёт их с помощью простой нейросети. Интерфейс реализован с использованием ASCII символов — можно нажимать "кнопки" и рисовать прямо в консоли.

![Главный экран](docs/example_1.png)
_Главный экран приложения_

---

## 🚀 Установка и запуск

1. **Склонируйте репозиторий:**

   Откройте командную строку или терминал и выполните команду для клонирования репозитория:

   ```bash
   git clone https://github.com/feed619/Neural-and-console-ui.git
   ```

2. **Запустите приложение**

   ```bash
   matrixpaint.exe
   ```

---

## Как использовать приложение

Рисование на холсте:
Чтобы начать рисовать символ, зажмите правую кнопку мыши и проведите курсором по холсту.

        Вы можете рисовать как символ X, так и O.

Распознавание символа:
После того как вы нарисовали символ, для его распознавания нажмите правой кнопкой мыши на кнопку "Start".

        Программа попытается распознать символ и отобразить результат.

Обучение нейросети:
Если распознавание не дало правильного ответа, вы можете обучить нейросеть:

            Для обучения символа X нажмите на кнопку "Is X".

            Для обучения символа O нажмите на кнопку "Is O".

        После этого нейросеть будет улучшать своё распознавание и сможет точнее определять символы.
