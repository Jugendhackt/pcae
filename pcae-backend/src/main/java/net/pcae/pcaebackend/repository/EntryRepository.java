package net.pcae.pcaebackend.repository;

import net.pcae.pcaebackend.model.EntryModel;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.query.Param;
import org.springframework.stereotype.Repository;

import java.util.List;

@Repository
public interface EntryRepository extends JpaRepository<EntryModel, Long> {

    @Query("SELECT e FROM EntryModel e WHERE e.latitude > :minLat AND e.latitude < :maxLat AND e.longitude > :minLon AND e.longitude < :maxLon")
    public List<EntryModel> findBetweenPoints(@Param("minLat") Double minLat, @Param("maxLat") Double maxLat, @Param("minLon") Double minLon, @Param("maxLon") Double maxLon);

}
