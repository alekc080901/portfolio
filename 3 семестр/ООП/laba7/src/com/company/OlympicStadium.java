package com.company;

import java.util.Random;

public class OlympicStadium extends OlympicConstruction implements RentObject {

    Random random = new Random();
    private final long price = random.nextInt(20) * 100 + 4000;

    public OlympicStadium(int number, String name) {
        super(number, name);
    }

    @Override
    void check() {
        System.out.printf("Номер олимпийского стадиона – %s; название – %s\n", this.getNUMBER(), this.getNAME());
    }

    @Override
    public void rent() {
        System.out.printf("Цена аренды стадиона: %d рублей в час\n", price);
    }

    @Override
    public long getPrice() {
        return price;
    }
}
