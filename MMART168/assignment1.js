const favMovieShow = [
    {
        name: "Kedi",
        releaseYear: 2017,
        genre: "documentary"

    },
    {
        name: "Avatar The Last Airbender",
        releaseYear: 2006,
        genre: "action drama"
    }
];

const Oakland = {
    name: "Oakland",
    population: 500000,
    mayor: "someone",
    cities: {
        name: "San Francisco",
        population: 700000
    }
}

let wedding = {

    bride: "jill",

    groom: "john",

    venue: "city hall san jose",

    date: "3/23/2022",

    invitations: [

        { family: "Jills brother's family", invited: 5, rsvped: 3, vegans: 1 },

        { family: "john's sister's family", invited: 3, rsvped: 1, vegans: 1 },

        { family: "Jills friend rachel", invited: 1, rsvped: 1, vegans: 0 },

        { family: "Jills uncles's family", invited: 10, rsvped: 2, vegans: 0 }

    ]

};

let numInvite, numRsvp, numVegan;
numInvite = numRsvp = numVegan = 0;

for(let i = 0; i < wedding.invitations.length;i++){
    numRsvp += wedding.invitations[i].rsvped;
    numInvite += wedding.invitations[i].invited;
    numVegan += wedding.invitations[i].vegans;
}

console.log("# of invitations: "+numInvite);

console.log("# of rsvp: "+numRsvp);

console.log("venue: "+ wedding.venue);

console.log("# of vegans: "+numVegan);