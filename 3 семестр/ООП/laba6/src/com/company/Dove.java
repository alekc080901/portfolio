package com.company;

public class Dove extends Bird {

    public Dove(String name) {
        super(name);
    }

    @Override
    public void motion() {
        System.out.println("Я летаю");
    }
}
