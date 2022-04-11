package com.company;

import java.util.Random;

public class Hostel extends SimpleConstruction implements RentObject {

    Random random = new Random();
    private final long price = random.nextInt(10) * 10 + 300;

    public Hostel(int number, String name) {
        super(number, name);
    }

    @Override
    public void repair() {
        System.out.println("Нам помогут студенты-строители на практике!");
    }

    @Override
    public void rent() {
        System.out.printf("Цена аренды общежития: %d рублей в час\n", price);
    }

    public long getPrice() {
        return price;
    }
}
