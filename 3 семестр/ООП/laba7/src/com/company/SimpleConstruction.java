package com.company;

public abstract class SimpleConstruction extends UniversityConstruction {

    public SimpleConstruction(int number, String name) {
        super(number, name);
    }

    public abstract void repair();
}
