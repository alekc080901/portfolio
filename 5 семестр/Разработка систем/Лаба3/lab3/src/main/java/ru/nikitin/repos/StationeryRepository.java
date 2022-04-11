package ru.nikitin.repos;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;
import ru.nikitin.entities.Stationery;

import java.util.List;

@Repository
public interface StationeryRepository extends JpaRepository<Stationery, Integer> {
    List<Stationery> findStationeryByManufacturer(String manufacturer);
}
