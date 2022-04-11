package com.company;

public class Lion extends Animal implements Exotic, Heatloving {

    public Lion(String name) {
        super(name);
    }

    @Override
    public void say() {
        System.out.println("Ррррр");
    }
}
