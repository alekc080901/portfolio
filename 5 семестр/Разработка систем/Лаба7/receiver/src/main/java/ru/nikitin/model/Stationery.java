package ru.nikitin.model;

import org.springframework.stereotype.Component;

@Component
public class Stationery {
    private Integer id;

    private String type;

    private Double price;

    private Integer amount;

    private String subtype;

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
