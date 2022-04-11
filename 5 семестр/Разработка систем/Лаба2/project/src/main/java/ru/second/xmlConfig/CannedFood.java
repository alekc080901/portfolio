package ru.second.xmlConfig;

import lombok.AllArgsConstructor;
import lombok.Data;

public @Data
@AllArgsConstructor
class CannedFood implements Portable{
    private String product;

    @Override
    public void showInfo() {
        System.out.println("Название объекта: консервы");
        System.out.println("Консервированный продукт: " + this.product.toLowerCase());
    }
}
