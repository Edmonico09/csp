domains = {
    "d_1": [0, 1, 2],  
    "d_2": [0, 1, 2],  
    "d_3": [0, 1, 2]  
}

constraints = [
    { "first_domain": "d_1", "second_domain": "d_2", "operation": "GT" },
    { "first_domain": "d_2", "second_domain": "d_1", "operation": "LT" },
    { "first_domain": "d_2", "second_domain": "d_3", "operation": "EQ" },
    { "first_domain": "d_3", "second_domain": "d_2", "operation": "EQ" }
]

def filter(domains, constraints):
    for constraint in constraints:
        
        
        if constraint["operation"] == "EQ":
            
            domains[constraint["first_domain"]] = { 
                                                   d_1 for d_1 in domains[constraint["first_domain"]] 
                                                   if any(d_1 == d_2 for d_2 in domains[constraint["second_domain"]])
                                                   }
            
        elif constraint["operation"] == "GT":
            domains[constraint["first_domain"]] = { 
                                                   d_1 for d_1 in domains[constraint["first_domain"]] 
                                                   if any(d_1 > d_2 for d_2 in domains[constraint["second_domain"]])
                                                   }
        
        elif constraint["operation"] == "LT":
            domains[constraint["first_domain"]] = { 
                                                   d_1 for d_1 in domains[constraint["first_domain"]] 
                                                   if any(d_1 < d_2 for d_2 in domains[constraint["second_domain"]])
                                                   }
            
        elif constraint["operation"] == "GTE":
            domains[constraint["first_domain"]] = { 
                                                   d_1 for d_1 in domains[constraint["first_domain"]] 
                                                   if any(d_1 >= d_2 for d_2 in domains[constraint["second_domain"]])
                                                   }
            
        elif constraint["operation"] == "LTE":
            domains[constraint["first_domain"]] = { 
                                                   d_1 for d_1 in domains[constraint["first_domain"]] 
                                                   if any(d_1 <= d_2 for d_2 in domains[constraint["second_domain"]])
                                                   }
    
    return domains

print("Domains: ", filter(domains, constraints))

