package com.company;

import java.io.Serializable;

public class Client implements Serializable {
    private final transient String NAME;
    private final int CARD_NUMBER;
    private final int AGE;
    private int receiptsSum = 0;

    public Client(String NAME, int AGE) {
        this.CARD_NUMBER = UniqueNumberGenerator.generate();
        this.NAME = NAME;
        this.AGE = AGE;
    }

    public void eat(Restaurant res, int sum) {
        receiptsSum += sum;
        res.addClient(this);
    }

    public int getCardNumber() {
        return CARD_NUMBER;
    }

    public String getName() {
        return NAME;
    }

    public int getAge() {
        return AGE;
    }

    public int getReceiptsSum() {
        return receiptsSum;
    }

    @Override
    public String toString() {
        return String.format("Имя: %s, Возраст: %d, Номер карты: %d, Потраченная сумма: %d\n",
                this.getName(), this.getAge(), this.getCardNumber(), this.getReceiptsSum());
    }
}
