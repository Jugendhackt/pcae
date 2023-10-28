package net.pcae.pcaebackend.model;

import jakarta.persistence.*;
import lombok.Data;

import java.sql.Timestamp;

@Entity
@Data
public class EntryModel {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;
    private Float co_value;
    private Double latitude;
    private Double longitude;
    @Temporal(TemporalType.TIMESTAMP)
    private Timestamp timestamp;
}
