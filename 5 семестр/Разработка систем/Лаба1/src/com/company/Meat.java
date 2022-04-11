package com.company;

import java.util.Objects;

public class Meat extends Product implements Weighable {
    private final double WEIGHT; // В килограммах
    public Meat(String productName, double price, double weight) {
        super(productName, price);
        this.WEIGHT = weight;
    }

    public double weigh() {
        return Math.round(this.WEIGHT * this.getPrice());
    }

    public double getWEIGHT() {
        return WEIGHT;
    }

    @Override
    public boolean equals(Object o) {
        if (!super.equals(o)) return false;
        Meat that = (Meat) o;
        return Double.compare(that.WEIGHT, this.WEIGHT) == 0;
    }

    @Override
    public int hashCode() {
        return Objects.hash(this.WEIGHT, this.getPrice(), this.getNAME());
    }

    @Override
    public String toString() {
        return "Название продукта: " + this.getNAME() + ";\n" +
                "Цена за кг: " + this.getPrice() + " рублей;\n" +
                "Вес: " + this.WEIGHT + " кг;\n" +
                "Итоговая цена: " + this.weigh() + " рублей.";
    }
}
