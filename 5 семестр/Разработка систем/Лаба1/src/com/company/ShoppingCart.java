package com.company;

import java.util.ArrayList;
import java.util.List;

public class ShoppingCart {
    private final ArrayList<Product> products = new ArrayList<>();

    public void putProduct(Product product) {
        this.products.add(product);
    }

    public void removeProduct(Product product) {

        this.products.remove(product);
    }

    public double getTotalPrice() {
        double totalPrice = 0.;
        for (Product product: this.products) {
            if (product instanceof Weighable)
                totalPrice += ((Weighable) product).weigh();
            else
                totalPrice += product.getPrice();
        }
        return Math.round(totalPrice);
    }

    public boolean isInCart(Product custom_product) {
        for (Product array_product: this.products) {
            return custom_product.equals(array_product);
        }
        return false;
    }

    public ArrayList<Product> getProducts() {
        return products;
    }
}
