package ru.nikitin.server.entities;

import lombok.AccessLevel;
import lombok.Setter;

import javax.persistence.*;
import javax.validation.constraints.Min;

@Entity
@Table(name = "stationery")
public class Stationery {
    @Id
    @Column(name = "id")
    @GeneratedValue(strategy= GenerationType.IDENTITY)
    @Setter(AccessLevel.NONE)
    private Integer id;

    @Column(name = "type")
    private String type;

    @Column(name = "price")
    @Min(0)
    private Double price;

    @Column(name = "amount")
    @Min(0)
    private Integer amount;

    @Column(name = "subtype")
    private String subtype;

    @Column(name = "manufacturer")
    private String manufacturer;

    public Stationery() {
    }

    public Stationery(String type, String subtype, Double price, Integer amount, String manufacturer) {
        this.type = type;
        this.price = price;
        this.amount = amount;
        this.subtype = subtype;
        this.manufacturer = manufacturer;
    }

    public Integer getId() {
        return id;
    }

    public String getType() {
        return type;
    }

    public Double getPrice() {
        return price;
    }

    public Integer getAmount() {
        return amount;
    }

    public String getSubtype() {
        return subtype;
    }

    public String getManufacturer() {
        return manufacturer;
    }

    public void setType(String type) {
        this.type = type;
    }

    public void setPrice(Double price) {
        this.price = price;
    }

    public void setAmount(Integer amount) {
        this.amount = amount;
    }

    public void setSubtype(String subtype) {
        this.subtype = subtype;
    }

    public void setManufacturer(String manufacturer) {
        this.manufacturer = manufacturer;
    }

    @Override
    public String toString() {
        return "id: " + this.id + " | " + "type: " + this.type + " | " + "subtype: " + this.subtype + " | "
                + "price: " + this.price + " | " + "manufacturer: " + this.manufacturer
                + " | " + "amount: " + this.amount;
    }
}
