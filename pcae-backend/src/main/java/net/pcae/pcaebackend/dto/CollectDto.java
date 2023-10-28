package net.pcae.pcaebackend.dto;

import lombok.AllArgsConstructor;
import lombok.Data;

import java.sql.Timestamp;

@Data
@AllArgsConstructor
public class CollectDto {

    public Double latitude;
    public Double longitude;
    public Timestamp timestamp;
    public Float co_value;

}
