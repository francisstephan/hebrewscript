let latheb : Js.Dict.t(string) = Js.Dict.fromList([("'",{js|א|js} ),("b" ,{js|ב|js}),("g",{js|ג|js}), ("d",{js|ד|js}),
  ("h",{js|ה|js}),("w" ,{js|ו|js}),("z" ,{js|ז|js}),("H" ,{js|ח|js}),("T" ,{js|ט|js}),("y" ,{js|י|js}),("k" ,{js|כ|js}),
  ("l" ,{js|ל|js}),("m" ,{js|מ|js}),("n" ,{js|נ|js}),("c" ,{js|ס|js}),("A" ,{js|ע|js}),("p" ,{js|פ|js}),("S" ,{js|צ|js}),
  ("q" ,{js|ק|js}),("r" ,{js|ר|js}),("s" ,{js|ש|js}),("t" ,{js|ת|js})]);

let lathebF : Js.Dict.t(string) = Js.Dict.fromList([("k",{js|ך|js} ),("m" ,{js|ם|js}),("n",{js|ן|js}), ("p",{js|ף|js}),
("S",{js|ץ|js})]);

let subst = (c : string, m : Js.Dict.t(string) ) : string => {
  switch (Js.Dict.get(m, c)) {
      | Some((car)) => car
      | None => c
  }
};
  
let trad = (s : string) :string => {
  let s2 = s ++ " "
  let subgen = (c:string,i:int) : string =>{
    let suc = Js.String2.charAt(s2,i+1); /* returns "" if i >= s.len */
    switch(suc) {
      | " " => switch(Js.Dict.get(lathebF , c)){
                 | Some((car)) => car
                 | None => subst(c,latheb)
               }
      | "" => ""
      | _   => subst(c,latheb)
    } 
  }
  s2
    -> Js.String2.castToArrayLike(_)
    -> Js.Array2.from(_)
    -> Js.Array2.mapi(_,subgen)
    -> Js.String2.concatMany("",_);
}; 

let translate = (s: option(string)) : string => {
    switch(s) {
      | Some(chaine) => trad(chaine)
      | None => "" 
    }
};

