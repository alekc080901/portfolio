package ru.second.annotationConfig;

import lombok.AllArgsConstructor;
import lombok.Data;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Component;

import javax.annotation.PostConstruct;
import javax.annotation.PreDestroy;

@Component
public @Data
class CannedFood implements Portable {
    @Value("${cannedFood.product}")
    private String product;

    @PostConstruct
    public void init() {
        System.out.println("Создание бина консервов.");
    }

    @Override
    public void showInfo() {
        System.out.println("Название объекта: консервы");
        System.out.println("Консервированный продукт: " + this.product.toLowerCase());
    }

    @PreDestroy
    public void destroy() {
        System.out.println("Бин консервов уничтожен.");
    }
}
