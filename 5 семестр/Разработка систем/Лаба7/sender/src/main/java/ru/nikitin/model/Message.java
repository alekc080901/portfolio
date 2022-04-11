package ru.nikitin.model;

import lombok.AllArgsConstructor;
import lombok.Data;
import ru.nikitin.entities.Stationery;

import java.io.Serializable;

public @Data
class Message implements Serializable {
    private String message;
    private Stationery stationery;

    public Message(String message, Stationery stationery) {
        this.message = message;
        this.stationery = stationery;
    }

    public String getMessage() {
        return message;
    }

    public Stationery getStationery() {
        return stationery;
    }

    public void setMessage(String message) {
        this.message = message;
    }

    public void setStationery(Stationery stationery) {
        this.stationery = stationery;
    }
}

