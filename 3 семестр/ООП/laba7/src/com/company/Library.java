package com.company;

public class Library extends SimpleConstruction {

    public Library(int number, String name) {
        super(number, name);
    }

    @Override
    public void repair() {
        System.out.println("Аккуратней с книгами!");
    }
}