package ru.nikitin.entities;

import lombok.AccessLevel;
import lombok.Setter;

import javax.persistence.*;

@Entity
public class Stationery {
    @Id
    @GeneratedValue(strategy= GenerationType.IDENTITY)
    @Setter(AccessLevel.NONE)
    @Column(updatable = false)
    private Integer id;

    @Column(nullable = false)
    private String type;

    @Column(nullable = false)
    private Double price;

    @Column(nullable = false)
    private Integer amount;

    @Column(nullable = false)
    private String subtype;

    @Column(nullable = false)
    private String manufacturer;

    public Stationery() {
    }

    public Stationery(String type, Double price, Integer amount, String subtype, String manufacturer) {
        this.type = type;
        this.price = price;
        this.amount = amount;
        this.subtype = subtype;
        this.manufacturer = manufacturer;
    }

    @Override
    public String toString() {
        return "id: " + this.id + " | " + "type: " + this.type + " | " + "subtype: " + this.subtype + " | "
                + "price: " + this.price + " | " + "manufacturer: " + this.manufacturer
                + " | " + "amount: " + this.amount;
    }
}
