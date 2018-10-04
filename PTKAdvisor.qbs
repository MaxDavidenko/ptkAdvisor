import qbs

Project {
    minimumQbsVersion: "1.9.1"
    references: ["ptkAdvisor.qbs", "dependencies/"+ String(qbs.buildVariant) + "/conanbuildinfo.qbs"]
}
