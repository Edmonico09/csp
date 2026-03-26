const domains: { [key: string]: number[] } = {
    "d_1": [0, 1, 2],  
    "d_2": [0, 1, 2],  
    "d_3": [0, 1, 2]  
}

const constraints: { d_1: string, d_2: string, operation: "GT" | "LT" | "GTE" | "LTE" | "EQ"}[] = [
    { d_1: "d_1", d_2: "d_2", operation: "GT"},
    { d_1: "d_2", d_2: "d_1", operation: "LT"},
    { d_1: "d_2", d_2: "d_3", operation: "EQ"},
    { d_1: "d_3", d_2: "d_2", operation: "EQ"}
]

const operations: { [key: string]: string } = {
    gt: "GT",
    lt: "LT",
    gte: "GTE",
    lte: "LTE",
    eq: "EQ" 
}

function filter_domain(domains: { [key: string]: number[] }) {
    constraints.map((constraint) => {
        const d_1 = domains[constraint.d_1]
        const d_2 = domains[constraint.d_2]
        const operation = constraint.operation

        if(operation === operations.eq) {
            domains[constraint.d_1] = d_1.filter( x => d_2.some(y => x == y))
        } else if (operation === operations.gt) {
            domains[constraint.d_1] = d_1.filter( x => d_2.some(y => x > y))
        } else if (operation === operations.lt) {
            domains[constraint.d_1] = d_1.filter( x => d_2.some(y => x < y))
        } else if (operation === operations.gte) {
            domains[constraint.d_1] = d_1.filter( x => d_2.some(y => x >= y))
        } else if (operation === operations.lte) {
            domains[constraint.d_1] = d_1.filter( x => d_2.some(y => x <= y))
        }

    })
}
  
filter_domain(domains)
console.log("Domains after: ", JSON.stringify(domains, null, 2))               
