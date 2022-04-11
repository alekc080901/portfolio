package ru.nikitin.services;

import ru.nikitin.entities.Stationery;

import java.util.List;
import java.util.Optional;

public interface StationeryService {
    boolean add(Stationery stationery);
    boolean delete(Integer id);
    boolean update(Integer id, Stationery stationery);
    List<Stationery> getByManufacturer(String manufacturer);
    List<Stationery> getAll();
    Optional<Stationery> get(Integer id);
}
