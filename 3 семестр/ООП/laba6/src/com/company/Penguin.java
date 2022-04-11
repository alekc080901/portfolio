package com.company;

public class Penguin extends Bird implements Exotic, Coldloving {

    public Penguin(String name) {
        super(name);
    }

    @Override
    public void motion() {
        System.out.println("Я плаваю");
    }
}
