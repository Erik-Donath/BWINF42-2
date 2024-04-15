import matplotlib
import matplotlib.pyplot as plt
import shapely.geometry as geo
import numpy as np
import math


def GenerateCirclePointsInPolygon(polygon: geo.Polygon, center: geo.Point, cradius: int, distance: int) -> list[geo.Point]:
    u = 2 * math.pi * cradius
    number_of_points = int(u // distance)
    distance = u / number_of_points

    cpoints: list[geo.Point] = []
    for i in range(number_of_points):
        at = i * distance
        radians = (at / u) * 2 * math.pi
        cpoint = geo.Point(math.cos(radians) * cradius + center.x, math.sin(radians) * cradius + center.y)

        if polygon.contains(cpoint):
            cpoints.append(cpoint)
    return cpoints


def renderPoints(rpoints: list[geo.Point], arg: str = "yo") -> None:
    xes: list[float] = []
    yes: list[float] = []

    for point in rpoints:
        xes.append(point.x)
        yes.append(point.y)
    plt.plot(xes, yes, arg)


if __name__ == '__main__':
    print(f"Matplot Version '{matplotlib.__version__}'")

    path = input("Enter a file path: ")
    vertices: list[geo.Point] = []
    with open(path, "r") as txt_file:
        count = int(txt_file.readline())
        for i in range(count):
            line = txt_file.readline()
            segments = line.split(" ")
            vertices.append(geo.Point(float(segments[0]), float(segments[1])))

    # Optionen
    # vertices: list[tuple[int, int]] = [(0, 0), (200, 200), (300, 200), (100, 300), (300, 320), (-50, 400)]
    renderGrid: bool = False
    gridDistances = 10
    radius = 85

    # Erstellen des Polygons
    polygon = geo.Polygon(vertices)
    plt.plot(*polygon.exterior.xy)

    # Finden der min und max punkte
    bound = polygon.bounds
    minPoint = geo.Point(bound[0], bound[1])
    maxPoint = geo.Point(bound[2], bound[3])

    # Generieren von Punkten
    print("Generating points")
    points: list[geo.Point] = []
    for x in np.arange(minPoint.x, maxPoint.x, gridDistances):
        for y in np.arange(minPoint.y, maxPoint.y, gridDistances):
            if polygon.contains(geo.Point(x, y)):
                points.append(geo.Point(x, y))
                if renderGrid:
                    plt.plot(x, y, 'bo')

    # Zählen der Punkte im Radius
    print(f"Counting points in distance {radius} [O(n²)={len(points) * len(points)}]")
    counts: dict[geo.Point, int] = {}
    for point in points:
        for other in points:
            if other.distance(point) <= radius:
                counts[point] = (counts[point] if point in counts else 1) + 1

    # Finden des besten Punktes durch Sortierung des Arrays
    print("Finding best point")
    counts = dict(sorted(counts.items(), key=lambda item: item[1]))
    if len(counts) == 0:
        print("=> No point found")
        plt.title("No point found")
        plt.show()
        exit(0)
    print(counts.values())
    lastPoint = list(counts.keys())[-1]

    # Zeichnet die Dörfer in dem Kreis im Abstand von 10
    print("Generating Villages in distance")
    cradius = 0
    for cradius in range(10, radius, 10):
        cpoints = GenerateCirclePointsInPolygon(polygon, lastPoint, cradius, 10)
        renderPoints(cpoints, "yo")

    print("Generating Villages outside distance")
    cradius += 20
    while True:
        cpoints = GenerateCirclePointsInPolygon(polygon, lastPoint, cradius, 20)
        if len(cpoints) == 0:
            break
        renderPoints(cpoints, "yo")
        cradius += 20

    # Debug
    print(f"Center: {lastPoint}")
    print(f"Min {minPoint} | Max {maxPoint}")
    plt.plot(lastPoint.x, lastPoint.y, "ro")
    plt.title(f"Gesundheitszentrum bei ({lastPoint.x}, {lastPoint.y})")

    plt.show()
