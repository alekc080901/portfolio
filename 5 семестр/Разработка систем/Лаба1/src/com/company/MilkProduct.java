package com.company;

import java.util.Objects;

public class MilkProduct extends Product {
    private final double FAT_CONTENT;
    public MilkProduct(String productName, double price, double fatContent) {
        super(productName, price);
        this.FAT_CONTENT = fatContent;
    }

    public double getFAT_CONTENT() {
        return FAT_CONTENT;
    }

    @Override
    public boolean equals(Object o) {
        if (!super.equals(o)) return false;
        MilkProduct that = (MilkProduct) o;
        return Double.compare(that.FAT_CONTENT, this.FAT_CONTENT) == 0;
    }

    @Override
    public int hashCode() {
        return Objects.hash(this.FAT_CONTENT, this.getPrice(), this.getNAME());
    }

    @Override
    public String toString() {
        return "Название продукта: " + this.getNAME() + ";\n" +
                "Цена: " + this.getPrice() + " рублей;\n" +
                "Жирность: " + this.FAT_CONTENT + "%.";
    }
}
