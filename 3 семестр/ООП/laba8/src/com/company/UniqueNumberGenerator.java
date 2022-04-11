package com.company;

import java.util.HashSet;
import java.util.Random;

public class UniqueNumberGenerator {

    private static final HashSet<Integer> usedNumbers = new HashSet<>();

    public static int generate() {
        Random random = new Random();

        int number;
        do {
            number = random.nextInt(90000) + 10000;
        } while (usedNumbers.contains(number));

        usedNumbers.add(number);
        return number;
    }
}
