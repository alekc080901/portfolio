package com.company;

public abstract class Product {
    private final String NAME;
    private double price;

    public Product(String productName, double price) {
        this.NAME = productName;
        this.price = price;
    }

    public abstract String toString();

    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null) return false;

        if (getClass() != o.getClass())
            return false;

        Product that = (Product) o;
        return Double.compare(that.getPrice(), this.getPrice()) == 0 &&
                that.getNAME().equals(this.getNAME());
    }

    public abstract int hashCode();

    public void setPrice(int price) {
        this.price = price;
    }

    public String getNAME() {
        return NAME;
    }

    public double getPrice() {
        return price;
    }
}
