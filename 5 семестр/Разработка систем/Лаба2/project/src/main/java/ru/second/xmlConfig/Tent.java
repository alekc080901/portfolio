package ru.second.xmlConfig;

import lombok.AllArgsConstructor;
import lombok.Data;

public @Data
@AllArgsConstructor
class Tent implements Portable {
    private int humanCapacity;

    @Override
    public void showInfo() {
        System.out.println("Название объекта: палатка");
        System.out.println("Вместимость палатки: " + this.humanCapacity + " человека");
    }
}
