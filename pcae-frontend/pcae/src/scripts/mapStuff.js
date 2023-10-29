let fetchDataPoints = async () => {

    let headers = new Headers();
    headers.set('Authorization', 'Basic ' + btoa("admin" + ":" + "admin"));
    headers.set('Content-Type', 'application/json')
    const response = await fetch('https://api-pcae.siefke.org/retrieve/between', {
        headers: headers,
        method: "POST",
        body: JSON.stringify({
            minLat: -10.0,
            maxLat: 600.0,
            minLon: -10.0,
            maxLon: 1100.0
        })
    });
    return response.json();
}

let dataCOColor = (co) => {
    let lowCO = 300
    let highCO = 750
    co = Math.min(Math.max(co, lowCO),highCO)
    let coScale = (co-lowCO)/(highCO-lowCO)
    return colorsys.hsv2Hex({h: 120-(coScale*120), s: 100, v: 100})
}

export { fetchDataPoints, dataCOColor };
