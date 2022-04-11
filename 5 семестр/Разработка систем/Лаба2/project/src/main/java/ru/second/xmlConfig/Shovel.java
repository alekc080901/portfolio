package ru.second.xmlConfig;

import lombok.AllArgsConstructor;
import lombok.Data;

public @Data
@AllArgsConstructor
class Shovel implements Portable {
    private ShovelTypes type;

    @Override
    public void showInfo() {
        System.out.println("Название объекта: лопата");
        System.out.println("Тип лопаты: " + this.type.name().toLowerCase());
    }
}
