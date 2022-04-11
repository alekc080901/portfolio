package com.company;

import java.util.concurrent.ThreadLocalRandom;

public class Patient {
    private final String NAME;
    private final double[] TEMPERATURE;
    private final double AVERAGE_TEMPERATURE;

    public Patient(String name) {
        this.NAME = name;
        this.TEMPERATURE = new double[]{ranDouble(35.0, 41.0), ranDouble(35.0, 41.0), ranDouble(35.0, 41.0),
                ranDouble(35.0, 41.0), ranDouble(35.0, 41.0), ranDouble(35.0, 41.0), ranDouble(35.0, 41.0)}; // 7
        this.AVERAGE_TEMPERATURE = averageNumber(TEMPERATURE);
    }

    public double ranDouble(double min, double max) {
        double randomValue = ThreadLocalRandom.current().nextDouble(min, max);
        randomValue = Math.round(randomValue * 10.0) / 10.0; // Округление до одного знака
        return randomValue;
    }

    public double averageNumber(double[] numbers) {
        double sum = 0;
        for (double i: numbers) {
            sum += i;
        }

        if (numbers.length > 0)
            return Math.round(sum / numbers.length * 10.0) / 10.0;
        else
            return 0;
    }

    public double[] getTEMPERATURE() {
        return TEMPERATURE;
    }

    public String getNAME() {
        return NAME;
    }

    public double getAVERAGE_TEMPERATURE() {
        return AVERAGE_TEMPERATURE;
    }
}
