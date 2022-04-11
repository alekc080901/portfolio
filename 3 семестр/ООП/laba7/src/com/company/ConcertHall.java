package com.company;

import java.util.Random;

public class ConcertHall extends OlympicConstruction implements RentObject {

    Random random = new Random();
    private final long price = random.nextInt(10) * 100 + 3000;

    public ConcertHall(int number, String name) {
        super(number, name);
    }

    @Override
    void check() {
        System.out.println("Номер концертного зала – " + this.getNUMBER());
    }

    @Override
    public void rent() {
        System.out.printf("Цена аренды концертного зала: %d рублей в час\n", price);
    }

    @Override
    public long getPrice() {
        return price;
    }
}
