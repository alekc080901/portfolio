package com.company;

public abstract class OlympicConstruction extends UniversityConstruction {

    public OlympicConstruction(int number, String name) {
        super(number, name);
    }

    abstract void check();
}
